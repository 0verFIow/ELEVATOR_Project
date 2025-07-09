#ifndef INC_FND_H_
#define INC_FND_H_

#include "main.h"
#include "ds1302.h"

void send_1byte_74hc595_fnd(uint8_t data);
void fnd_init(void);
void fnd_main();
void fnd_test_main();



#endif /* INC_FND_H_ */
