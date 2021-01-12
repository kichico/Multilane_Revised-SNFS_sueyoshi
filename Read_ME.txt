When you study this single lane program, you should read based on this order I recommend.

1) Multilane_traffic_flow
2) Car_information
3) Map_information
4) Initialize
5) Decide_velocity
6) Update_position

from Initialize, each class is inherited to next row class, except for Update_position, which is inherited to Multilane_traffic_flow

In my code, "class" is the biggest wrap in each file, while "struct" is things that includes the list of some parameters.
"Private" is the things of not called by other code. When you write some program, you should using this private class; private parameters are not allowed to rewrite except for relevant class, very safety.
