// MANUAL DRIVE

#define OSCADDR_FORWARD_STEP 		"/kronos/go/fwd"
#define OSCADDR_REWIND_STEP 		"/kronos/go/back"
#define OSCADDR_GO 					"/kronos/go/by"		// pass an integer value relative to current position
#define OSCADDR_RESET				"/kronos/reset"		// rewinds until stopped (ie by home switch)

// PERFORMANCE

#define OSCADDR_DEPLOY 				"/kronos/perf/deploy"
#define OSCADDR_UNDEPLOY 			"/kronos/perf/undeploy"
#define OSCADDR_STUNT 				"/kronos/perf/stunt"

// HOME

#define OSCADDR_GO_HOME 			"/kronos/home/go"
#define OSCADDR_SET_HERE_HOME 		"/kronos/home/here"
#define OSCADDR_GO_HOME_PLUS		"/kronos/home/plus"		// pass an integer value relative to home

// RELATIVE TO HOME

#define OSCADDR_GO_KF 				"/kronos/kf/go"			// pass an integer keyframe index
#define OSCADDR_SET_HERE_KF 		"/kronos/kf/here"

// HANDSHAKE / REPLY OVER OSC