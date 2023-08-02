apt-get -y update
apt-get -y upgrade
apt-get -y install ffmpeg
apt-get -y install git
apt-get -y install netcat
sudo -u pi git clone https://github.com/WiringPi/WiringPi
cd WiringPi; ./build; cd ..
sudo -u pi git clone https://github.com/bitfixer/petpix_v3.git
cd petpix_v3; git submodule init; git submodule update; cd ..

# this part sets up a self hosted access point
# disabling for now for ease of debugging

# apt-get -y install hostapd
# systemctl unmask hostapd
# systemctl enable hostapd
# apt-get -y install dnsmasq

# mv /etc/dhcpcd.conf /etc/dhcpcd.conf.orig
# cp petpix_v3/setup/dhcpcd.conf /etc/dhcpcd.conf

# mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
# cp petpix_v3/setup/dnsmasq.conf /etc/dnsmasq.conf
# rfkill unblock wlan
# cp petpix_v3/setup/hostapd.conf /etc/hostapd/hostapd.conf

# install startup script
mkdir /mnt/tmp
cp petpix_v3/setup/rc.local /etc/rc.local

# apache
apt-get -y install apache2
apt-get -y install php
openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout private.key -out certificate.crt
mv private.key /etc/ssl/private/
mv certificate.crt /etc/ssl/certs/
cp petpix_v3/setup/000-default.conf /etc/apache2/sites-available/000-default.conf
cp petpix_v3/setup/php.ini /etc/php/7.4/apache2/php.ini
a2enmod ssl
systemctl restart apache2.service

cd petpix_v3; make all; cd ..
cp -r petpix_v3/html/* /var/www/html/
mkdir /var/www/html/bin
cp petpix_v3/bin/convert_one_video /var/www/html/bin
cp petpix_v3/bin/petscii_convert /var/www/html/bin
rm /var/www/html/index.html
chmod 777 /var/www/html/uploads
reboot
