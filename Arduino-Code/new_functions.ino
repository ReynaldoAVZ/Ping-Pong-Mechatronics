// rearranges the order of the targets so targets closest to reloader go first
// and farthest go last
void BestTargetAndAngleOrder(void){
  int holderStripe;
  int holderAngle;
  for(int i = 0; i < 6; ++i){
    for(int j = 0; j < 5; ++j){
      if (driveTo[j] < driveTo[j + 1]){
        holderStripe = driveTo[j + 1];
        holderAngle = writeToServo[j + 1];
        driveTo[j + 1] = driveTo[j];
        writeToServo[j + 1] = writeToServo[j];
        driveTo[j] = holderStripe;
        writeToServo[j] = holderAngle;
      }
    }
  }
}
