#!/bin/sh


#script options
#
gOptionInit="init"
gOptionDecode="decode"
gOptionEncode="encode"
gOptionClean="cleanup"
gOptionPeek="peek"


#usage string
#
gDecoratingTabs="\t"
gUsageString="USER MANUAL:________\n\n\n\
PreRequisite:\n\
* This must be a Linux System\n\
* In Terminal, Current directory should be the folder containing coDEcode.sh\n\
* Files: SecureFolder.gpg in current directory.\n\
* Folders : ~\Desktop, ~\Desktop\SecureFolder, .\Archive must be available and accessible\t\t\n(use sh coDEcode.sh $gOptionInit for this)\n\n\n\
Usage:\n\
+ Initialize (run this the first time!, creates a folder in desktop that you can encrypt.) :$gDecoratingTabs sh coDEcode.sh $gOptionInit\n\
+ Load in Desktop (run this to decrypt and load your secret data into desktop.) :$gDecoratingTabs sh coDEcode.sh $gOptionDecode\n\
+ Save From Desktop (run this to encrypt your secret data from desktop and store it.) :$gDecoratingTabs sh coDEcode.sh $gOptionEncode\n\
+ Cleanup Desktop (run this to clean any data that may reside in desktop un-intentionally) :$gDecoratingTabs sh coDEcode.sh $gOptionClean\n\
+ Peek Contents (quick peek the contents of your encrypted data.) :$gDecoratingTabs sh coDEcode.sh $gOptionPeek [ <Path/To/File/Inside/Encoded/Folder> ]\n\n\
____________________"


##variables
#
gCurrentTime=`date "+%Y%m%d%H%M%S"`
gEncodedDataFolderName="ProtectedData"
gEncodedDataFileNamePrefix="EncodedData.tgz.gpg"

gCurrentDirPath=`pwd`  #path where the secure data is located.
gEditingDir=`eval echo ~/Desktop` #path where the secure data will be loaded for edit.
gArchiveFolderName="Archive" #path for archiving/backup.

gTempCompressedFile="tempEncodedData.tgz"


##paths
#
# directory where the encrypted data is stored & also the place where script is run.
gEncodedDataEncryptedFilePathPrefix="$gCurrentDirPath/$gEncodedDataFileNamePrefix."
# another directory inside gCurrentDir, that stores backup of the encrypted data.
gArchiveDirPath="$gCurrentDirPath/$gArchiveFolderName"
# working/editing directory where user can load->edit->save the encrypted data.
gEncodedDataEditingDirectoryPath="$gEditingDir/$gEncodedDataFolderName"
#temp directory.
gTempCompressedFilePath="$gEditingDir/$gTempCompressedFile"

##function to print usage.
#
printUsage()
{
  clear
  echo $gUsageString
}

##function to init()
#
performInit()
{
	if [ ! -d $gEncodedDataEditingDirectoryPath ]
	then
		mkdir "$gEncodedDataEditingDirectoryPath"
	fi

	if [ ! -d "$gArchiveDirPath" ]
	then
		mkdir "$gArchiveDirPath"
	fi
}

##function to perform Load To Desktop
#
performLoad()
{
	
	secureDataFile=`ls | grep $gEncodedDataFileNamePrefix`
	if [ ! -f $secureDataFile ]
	then
		echo "performLoad: $gEncodedDataFileNamePrefix... doesnot exist."
		return 1
	fi
	secureDataFileFullPath=$gCurrentDirPath/$secureDataFile

	

	# keep the desktop ready for coping.
	#
	performClean

	# cleanup intermediate directory.
	#
	rm -f "$gTempCompressedFilePath"

	#
	#
	echo "please provide appropriate details for loading: $secureDataFile"
	
	# gpg -o dest -d src
	#
	gpg -o "$gTempCompressedFilePath" -d "$secureDataFileFullPath"
    # tar -xzvf src -C dest
    #
    tar -xzvf "$gTempCompressedFilePath" -C "$gEditingDir"
    
    rm -f "$gTempCompressedFilePath"

}

##function to perform Save From Desktop
#
performSave()
{

	# check for source directory is present.
	#
	if [ ! -d $gEncodedDataEditingDirectoryPath ]
	then
		echo "performSave: $gEncodedDataEditingDirectoryPath doesnot exist."
		return 1
	fi

	
	#Get Clue.
	#
	echo "Saving the data into secure folder..."
	echo
	echo "Please provide a password clue string/word(alphaNumeric) for the data you are going to store:"
	read clue
	CLUELENGTH=$(echo -n $clue | wc -m)
	if [ $CLUELENGTH -eq 0 ]
	then
		echo "performSave: clue is not proper."
		return 1
	fi


	rm -f "$gTempCompressedFilePath"
	## tar -czvf dest -C src-dir-parent-path src-dir-name
	#
	tar -czvf "$gTempCompressedFilePath" -C "$gEditingDir" "$gEncodedDataFolderName"

	##
	#
	# If something got compressed, following gpg will also suceed. 
	# TBD: dont remove this blindly, add additional check for gpg sucess.
	if [ -f "$gTempCompressedFilePath" ]
	then
		pwd
		echo "rm -f $gEncodedDataFileNamePrefix*"
		rm -f $gEncodedDataFileNamePrefix*
	fi

	## gpg -o dest --symmetric --cipher-algo AES256 src
	#
	gpg -o "$gEncodedDataEncryptedFilePathPrefix$clue" --symmetric --cipher-algo AES256 "$gTempCompressedFilePath"
	cp "$gEncodedDataEncryptedFilePathPrefix$clue" "$gArchiveDirPath/$gEncodedDataFileNamePrefix.$clue.$gCurrentTime"
	rm -f "$gTempCompressedFilePath"

	
	performClean
}

##function to perform Clean of Desktop
#
performClean()
{
   if [ -d $gEncodedDataEditingDirectoryPath ]
   then
   #echo "performClean"
   rm -rf "$gEncodedDataEditingDirectoryPath"
   else
   echo performClean: $gEncodedDataEditingDirectoryPath does not exist.
   fi
   
}

##function to peek of encrypted data.
#
performPeek()
{
	#Load the data for Peeking.
	#
	performLoad

	#echo "performPeek" $1
	if [ $# -eq 0 ]
	then
		pushd $gEncodedDataEditingDirectoryPath
		find .
		popd
	else
		pushd $gEncodedDataEditingDirectoryPath
		pwd
		cat "$1"
		popd
	fi

	#Clear the data after the Peeking.
	#
	performClean


}

##begin.
#

#check if directory contains the script.
#
scriptFileName=$0
lsOutput=`ls | grep $scriptFileName`
if [ ! -f $lsOutput ]
then
printUsage
exit 1
fi

#check if arguments are proper.
#
if [ $# -lt 1 ]
then
printUsage
exit 1
fi

case $1 in
   $gOptionInit)
   performInit
   ;;
   $gOptionDecode) 
   performLoad 
   ;;
   $gOptionEncode) 
   performSave
   ;;
   $gOptionClean) 
   performClean
   ;;
   $gOptionPeek)
   if [ $# -lt 2 ]
   then
   		performPeek
   else
   		performPeek $2
   fi
   ;;
   *) 
   printUsage
   ;;
esac

exit 0

#Some-Links:
#https://stackoverflow.com/questions/28247821/openssl-vs-gpg-for-encrypting-off-site-backups
#https://en.wikipedia.org/wiki/Advanced_Encryption_Standard
#https://www.tutonics.com/2012/11/gpg-encryption-guide-part-4-symmetric.html


