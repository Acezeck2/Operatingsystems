#!/bin/bash
# Hardening Apache Server

CONFIG='/etc/apache2/apache2.conf'


echo -n '> Updating Apache... '

apt update apache2 >/dev/null 2>&1 &
SUCCESS=$?

if [ $SUCCESS -eq 0 ]; then
    echo "[Success]"
else
    echo "[Mislukt]"
fi

# Backing Up Original Configuration

echo -n '> Back-up maken van configuratie... '
cp $CONFIG "$CONFIG.bk" &

SUCCESS=$?

if [ $SUCCESS -eq 0 ]; then
    echo "[Success]"
else
    echo "[Mislukt]"
fi

# Protect Apache Binary Files

echo -n '> Beschermen van Apache Binary Files... '

chown -R root:root /etc/httpd/conf /etc/httpd/bin >/dev/null 2>&1 &
chmod -R 750 /etc/httpd/conf /etc/httpd/bin >/dev/null 2>&1 &

SUCCESS=$?

if [ $SUCCESS -eq 0 ]; then
    echo "[Success]"
else
    echo "[Mislukt]"
fi


# Restart Apache Server

echo 'Apache opnieuw opgestart!'

service apache2 restart &

