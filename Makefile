bwlogd: bwlogd.cpp
	g++ bwlogd.cpp -o bwlogd-json -lstatgrab
install: bwlogd
	mkdir -p /usr/local/bin
	cp bwlogd-json /usr/local/bin
uninstall:
	rm -f /usr/local/bin/bwlogd-json
clean:
	rm -f bwlogd-json
