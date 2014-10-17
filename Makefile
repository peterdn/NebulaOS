all:
		cd src; $(MAKE) $(MFLAGS)

clean:
		cd src; $(MAKE) clean

bootdisk: all
		sudo scripts/create_bootdisk

bochs: bootdisk
		scripts/run_bochs
