bwlogd: bwlogd.cpp
	g++ bwlogd.cpp -o bwlogd -lstatgrab
install: bwlogd
	mkdir -p /usr/local/bin
	cp bwlogd /usr/local/bin
uninstall:
	rm -f /usr/local/bin/bwlogd
clean:
	rm -f bwlogd
