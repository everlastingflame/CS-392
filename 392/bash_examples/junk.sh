#!/bin/bash
# Credit: https://www.computerhope.com/unix/bash/getopts.htm

readonly junkFolder=~/.junk

FLAG=0   

usage() {                                 # Function: Print a help message.
  cat << hereDoc
Usage: $(basename "$0") [-hlp] [list of files]
   -h: Display help.
   -l: List junked files.
   -p: Purge all files.
   [list of files] with no other arguments to junk those files.
hereDoc
}

exit_abnormal() {                         # Function: Exit with error.
  echo "Error: Too many options enabled." >&2
  usage
  exit 1
}

flagCheck() {
 if [[($FLAG > 0)]]; then
   exit_abnormal
 fi
}

listing=0
purge=0


while getopts ":hlp" options; do                                 
  case "${options}" in                    
    h)
      if [[($# > 1)]]; then
       exit_abnormal
      fi
      flagCheck                              
      usage
      FLAG=$(($FLAG + 1))
      exit 0
      ;;

    l)
      if [[($# > 1)]]; then
       exit_abnormal
      fi
      flagCheck                                            
      FLAG=$(($FLAG + 1))
      listing=2
      ;;

    p)
      if [[($# > 1)]]; then
       exit_abnormal
      fi
      flagCheck
      FLAG=$(($FLAG + 1))
      purge=3
      ;;
    *)                                                 # If unknown (any other) option:
      echo $'Error: Unknown argument \'-'$OPTARG$'\'.' >&2
      usage                       # Exit abnormally.
      exit 1
      ;;
  esac
done

if [[($# == 0)]]; then
   usage                        #check for no arguments
   exit 0
fi

shift "$((OPTIND-1))"           #clear arguments for script running

#searching for files/purging/etc etc

if [ ! -d "$junkFolder" ]; then                       #create recycling bin
	mkdir "$junkFolder"                
	exit 0
fi

junkSearch(){
 ls -lAF "$junkFolder"                                #search recycling bin
 exit 0
}

junkPurge(){
  rm -rf $junkFolder/* $junkFolder/.* 2>/dev/null     #empty recycling bin
  exit 0
}

 if [[($listing > 0)]]; then
   junkSearch
 fi

 if [[($purge > 0)]]; then
   junkPurge
 fi

location=0

for i in $@; do
	filenames[$location]="$i"
	((++index))
done

for n in ${filenames[@]}; do
	if [ ! -e "$n" ] ; then
		printf "Warning: '$n' not found. \n" >&2
	else
		mv $n $junkFolder
	fi
done

exit 0                                    # Exit normally.
