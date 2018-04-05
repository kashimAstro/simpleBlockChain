#include "Chain.h"

int main(int argc, char ** argv)
{
    if(argc < 2){
       cout << "Parameter: difficult" << endl;
       return -1;
    }
    int d = atoi(argv[1]);
    Blockchain bChain = Blockchain(d);
    for(int i = 0; i < 100; i++) {
       cout << "mining block: " << i << endl;
       bChain.add(Block(i, "block "+to_string(i)));
    }
    return 0;
}
