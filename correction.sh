#!/bin/bash

set -e

do_init() {
    do_clone
    do_gitignore
}

do_clone() {
    input="./git_repos.txt"
    while IFS= read -r line
    do
        echo Cloning $line
		sleep 5
        targetdir=`echo $line | cut -c32- | awk -F'/' '{print $1}'`
        echo "$targetdir"
        git clone $line $targetdir || true
    done < "$input"
}

do_gitignore() {
 for D in `find . -maxdepth 1 -type d ! -path .`
    do
        echo "
# MacOS
.DS_Store
# Latex
*.aux
*.bbl
*.blg
*.log
*.nav
*.out
*.snm
*.toc
*.vrb
*.run.xml
*.bcf
*.synctex.gz

# C
*.d
*.i
*.s
*.o
*.ko
*.obj
*.elf
*.ilk
*.map
*.exp
*.gch
*.pch
*.lib
*.a
*.la
*.lo
*.dll
*.so
*.so.*
*.dylib
*.exe
*.out
*.app
*.i*86
*.x86_64
*.hex
*.dSYM/
*.su
*.idb
*.pdb
*.mod*
*.cmd
.tmp_versions/
modules.order
Module.symvers
Mkfile.old
dkms.conf
        " >> $D/.gitignore
    done
    do_push
}

do_pull() {
    for D in `find . -maxdepth 1 -type d ! -path .`
    do
        echo Pulling $D
        git -C "$D" pull
		sleep 5
    done
}

do_tag() {
    do_pull
    for D in `find . -maxdepth 1 -type d ! -path .`
    do
        echo Tagging $D
        git -C $D tag $(date +%d.%m.%Y-%H%M) 
        git -C $D push origin --tags
		sleep 5
    done
}

do_push() {
 for D in `find . -maxdepth 1 -type d ! -path .`
    do
        echo Pushing $D
        git -C $D add .
        git -C $D commit -m "correction"
        git -C $D push
		sleep 5
    done
}

do_status() {
 for D in `find . -maxdepth 1 -type d ! -path .`
	do
		echo $D
		git -C "$D" status
	done
}

do_ex() {
 for D in `find . -maxdepth 1 -type d ! -path .`
	do
		echo -e "\e[32m$D\e[39m"
		if [[ $(ls -I desktop.ini "$D/Abgaben/Blatt$1" 2>&1) ]]; then
			if [[ $(ls -I desktop.ini "$D/Abgaben/Blatt$1" 2>&1 | grep "ls: cannot access") ]]; then
				echo -e "\e[31mno directory\e[39m"
			else
				ls -I desktop.ini "$D/Abgaben/Blatt$1"|| true
			fi
		else
			echo -e "\e[33mno files found\e[39m"
		fi
		
	done
}



############# Main #############
show_help() {
cat << EOF
Correction Helper Script for the Operating systems course WS20/21. 
Supported commands:
    pull    --- Pull all repositories in this directory
    push    --- Adds all changes made to a directory, commits and pushes them
    tag     --- Creates a tag in all repositories in this directory to mark a submission deadline
	status	--- Show status
	ex %i%	--- Show Abgaben folder colored-status for exercise %i%
	# Initial# 
	init    	--- Inizialize by cloning student repositories and adding different file types to the .gitignore
    clone       --- Clones the repositories of the students specified in students.txt
    gitignore   --- Sets up the .gitignore file such that latex and C temp files are excluded
EOF
}

execute() {
    case "$1" in
        init|clone|gitignore|tag|pull|push|status|ex)
            command=$1
            shift
            do_${command} $@
            ;;
        *)
            printf "Unknown argument $1"
            show_help
            exit 1
            ;;
    esac
}

if [[ $# == 0 ]]; then show_help; exit 0; fi
execute $@

