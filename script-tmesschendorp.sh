export DEST=$HOME/Pictures/
if [ -d $DEST ]
then
	echo -e "$DEST bestaat al, script gaat verder.\n"
else
	echo -e "Folder aanmaken. $DEST..."
	mkdir $DEST
	echo -e "Folder is aangemaakt! !\n"
fi

echo -e "Graag het volledige path geven naar de source directory:"
read SRC
echo -e "Source directory: $SRC \n"
echo -e "Kies tussen maand of week: (month/week):"
read CHOICE

if [[ "$CHOICE" == "week" ]]
then
	export TARGET=$(find "$SRC" -name "*.jpg" -mtime +7)
elif [[ "$CHOICE" == "month" ]]
then
	export TARGET=$(find "$SRC" -name "*.jpg" -mtime +31)
else
	echo -e "Keuze $CHOICE is geen optie. Shutting down."
	exit 1
fi

echo -e "Kopie van alle fotos van laaste $CHOICE.\n"

for I in $TARGET
do
	if [[ "$CHOICE" == "week" ]]
	then
		if ! [ -d $DEST/week ]
		then
			mkdir $DEST/week
		fi
		export DATE=$(stat -c %y $I | cut -d' ' -f1)
		export WEEK=$(date --date="$DATE" +"%V")
		if ! [ -d $DEST/week/$WEEK ]
		then
			mkdir $DEST/week/$WEEK
		fi
		export NEWDEST=$DEST/week/$WEEK
		echo -e "$WEEK"
	else
		if ! [ -d $DEST/month ]
		then
			mkdir $DEST/month
		fi
		export MONTH=$(date +%B -r $I)
		if ! [ -d $DEST/month/$MONTH ]
		then
			mkdir $DEST/month/$MONTH
		fi
		export NEWDEST=$DEST/month/$MONTH
		echo -e "$MONTH"
	fi

	export NAME=$(basename $I)
	echo -e "Copying $I to $NEWDEST."
	cp $I $NEWDEST/$NAME

	export HASHORG=$(md5sum $I)
	export HASHNEW=$(md5sum $NEWDEST/$NAME)
	echo -e "Original hash: $HASHORG"
	echo -e "New hash: $HASHNEW"
	if [[ "$HASHORG == $HASHNEW" ]]
	then
		echo -e "Hashes komen overeen. Origineel word verwijdert.\n"
		rm $I
	else
		echo -e "Hashes komen niet overeen. \n"
		rm $NEWDEST/$FILENAME
	fi
done
echo -e "Succesvol! Foto's kun je nu vinden in:  $DEST."
#Tim M#