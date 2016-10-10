#! /usr/bin/tclsh
# vim: autoindent shiftwidth=2 softtabstop=2 tabstop=2 :

set VAL_NODES {16 32 64 128}
set INC 0.5

foreach NODE $VAL_NODES {
	set AREA 30000
	while {$AREA > 0} {
		puts stderr "./enumerating $NODE $AREA"
		exec ./enumerating $NODE $AREA >> n$NODE.txt
		set AREA [expr {$AREA - $INC}]
	}
}
