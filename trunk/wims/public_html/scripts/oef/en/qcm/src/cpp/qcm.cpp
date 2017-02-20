target=serial ordered shuffle stepserial stepordered stepshuffle

#include "xiao.inc"

\text{datafile=slib(oef/env datafile)}
\integer{datacnt=wims(recordcnt \datafile)}
\text{shuff=shuffle(\datacnt)}
#include "confparm.inc"

#if defined TARGET_serial
\title{Continuing questions}
\integer{start=randint(0..\datacnt-\questions)}
\text{records=wims(values x+\start for x=1 to \questions)}
\text{steptype=all}
#endif

#if defined TARGET_ordered
\title{Random questions in the original order}
\text{shuff=shuffle(\datacnt)}
\text{records=wims(sort numeric items \shuff[1..\questions])}
\text{steptype=all}
#endif

#if defined TARGET_shuffle
\title{Shuffled random questions}
\text{shuff=shuffle(\datacnt)}
\text{records=\shuff[1..\questions]}
\text{steptype=all}
#endif

#if defined TARGET_stepserial
\title{One by one continuing}
\integer{start=randint(0..\datacnt-\questions)}
\text{records=wims(values x+\start for x=1 to \questions)}
\text{steptype=step}
#endif

#if defined TARGET_stepordered
\title{One by one in the original order}
\text{shuff=shuffle(\datacnt)}
\text{records=wims(sort numeric items \shuff[1..\questions])}
\text{steptype=step}
#endif

#if defined TARGET_stepshuffle
\title{One by one shuffled}
\text{shuff=shuffle(\datacnt)}
\text{records=\shuff[1..\questions]}
\text{steptype=step}
#endif

\text{choicename=Choice}

#include "proc.inc"

