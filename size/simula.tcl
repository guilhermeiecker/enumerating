#! /usr/bin/tclsh
# vim: autoindent shiftwidth=2 softtabstop=2 tabstop=2 :

set MAXLINK 64;
set MAXRUNS 100;

set VAL_NODES {16}

foreach NODE $VAL_NODES {
	set LINK 4
	while {$LINK <= $MAXLINK} {
		set RUNS 0
		while {$RUNS < $MAXRUNS} {
			puts stderr "./recursive $NODE $LINK $RUNS"
			exec ./recursive $NODE $LINK $RUNS >> ../output/size-$NODE.txt
			exec printf "\t" >> ../output/size-$NODE.txt
			incr RUNS
		}
		exec printf "\n" >> ../output/size-$NODE.txt
		incr LINK
	}
}
