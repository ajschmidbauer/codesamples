#!/bin/bash

#Alexander J. Schmidbauer

if [ -s records.txt ]
then
	echo Using Preexisting Record System...
else
	>records.txt
fi

case $1 in
 -e)
  echo Choose a record to edit:
  echo Record/Name/Address/Phone/Email
  grep -n $2 records.txt
  read linenum
  record=$(sed -n "${linenum}p" records.txt)
  echo Edit the record:
  read -e -i "$record" input
  echo "$input">>records.txt
  sed -i "${linenum}d" records.txt
  echo Record Edited.
  ;;
 -r)
  echo Choose a record to remove:
  echo Record/Name/Address/Phone/Email
  grep -n $2 records.txt
  read str
  sed -i "${str}d" records.txt
  echo Record removed.
  ;;
 -a)
  echo Input name:
  read -e -i "(name)" name
  echo Input address:
  read -e -i "(address)" address
  echo Input phone:
  read -e -i "(phone)" phone
  echo Input email:
  read -e -i "(email)" email
  echo "$name $address $phone $email">>records.txt
  echo Record added.
  ;;
 *)
  echo These records match your key:
  echo Record/Name/Address/Phone/Email
  grep -n $1 records.txt
  ;;
esac

