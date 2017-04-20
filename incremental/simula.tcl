#! /usr/bin/tclsh
# vim: autoindent shiftwidth=2 softtabstop=2 tabstop=2 :

set VAL_NODES {100}
set INC 1000

foreach NODE $VAL_NODES {
	set AREA 4000
	set RUN 23
	while {$RUN < 101} { 
		puts stderr "./main $NODE $AREA $RUN"
		exec ./main $NODE $AREA $RUN >> results/$NODE.txt
		incr RUN
	}
}

foreach NODE $VAL_NODES {
        set AREA 3000
        while {$AREA > 0} {
                set RUN 1
                while {$RUN < 101} {
                        puts stderr "./main $NODE $AREA $RUN"
                        exec ./main $NODE $AREA $RUN >> results/$NODE.txt
                        incr RUN
                }
                set AREA [expr {$AREA - $INC}]
        }
}
