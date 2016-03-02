/*
 * Batterie.cpp
 *
 *  Created on: 1 mars 2016
 *      Author: fllor_000
 */

#include "Batterie.h"

Batterie::Batterie() {
	calculBatterie();
	// TODO Auto-generated constructor stub

}

Batterie::~Batterie() {
	// TODO Auto-generated destructor stub
}

void Batterie::calculBatterie(){
    printf("AnalogInputOutput\n");

    /*
     * Specify the registers that correspond to the AIO channel
     * that needs to be accessed.
     *
     * Assign constants to the weight and offset of the connector.
     */
    A0.val = AIA_0VAL;
    A0.wght = AIA_0WGHT;
    A0.ofst = AIA_0OFST;
    A0.is_signed = NiFpga_False;

    A3.val = AIA_3VAL;
    A3.wght = AIA_3WGHT;
    A3.ofst = AIA_3OFST;
    A3.is_signed = NiFpga_False;

    B0.val = AOB_0VAL;
    B0.wght = AOB_0WGHT;
    B0.ofst = AOB_0OFST;
    B0.set = AOSYSGO;
    B0.is_signed = NiFpga_True;

    /*
     * Open the myRIO NiFpga Session.
     * This function MUST be called before all other functions. After this call
     * is complete the myRIO target will be ready to be used.
     */
    status = MyRio_Open();
    if (MyRio_IsNotSuccess(status))
    {
        return;
    }

    /*
     * Read the scaling factors, initializing the struct
     */
    Aio_Scaling(&A0);
    Aio_Scaling(&A3);
    Aio_Scaling(&B0);

    /*
     * Read from AI channels A/AI0 and A/AI3.
     * Each channel is on Connector A.
     */
    ai_A0 = Aio_Read(&A0);
    ai_A3 = Aio_Read(&A3);

    /*
     * Print out the logic level of each channel.
     */
    printf("A/AI0 = %f\n", ai_A0);
    printf("A/AI3 = %f\n", ai_A3);

    /*
     * Calculate the difference between the channels
     */
    ao_B0 = ai_A0 - ai_A3;

    /*
     * Print out the desired logic level of B/AO0.
     */
    printf("B/AO0 = %f\n", ao_B0);

    /*
     * Write to channel B/AO0 to set it to the desired value.
     */
    Aio_Write(&B0, ai_A0);

    //4.9/5*100

    niveauBatterie = ((ai_A0/5*100)+(ai_A3/3.3*100))/2;

    /*
     * Normally, the main function runs a long running or infinite loop.
     * Keep the program running so that you can measure the output from B7 using
     * an external instrument.
     */
    time(&currentTime);
    finalTime = currentTime + LoopDuration;
    while (currentTime < finalTime)
    {
        time(&currentTime);
    }

    /*
     * Close the myRIO NiFpga Session.
     * This function MUST be called after all other functions.
     */
    status = MyRio_Close();

    /*
     * Returns 0 if successful.
     */

}

int Batterie::getBatterie(){
	return niveauBatterie;
}
