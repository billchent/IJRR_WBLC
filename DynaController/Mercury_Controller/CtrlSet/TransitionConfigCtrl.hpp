#ifndef TRANSITION_CONFIGURATION_CONTROLLER
#define TRANSITION_CONFIGURATION_CONTROLLER

#include <Controller.hpp>

class RobotSystem;
class Mercury_StateProvider;
class WBLC_ContactSpec;
class WBLC;
class KinWBC;
class WBLC_ExtraData;

class TransitionConfigCtrl: public Controller{
public:
  TransitionConfigCtrl(RobotSystem* robot, int moving_foot, bool b_increase);
  virtual ~TransitionConfigCtrl();

  virtual void OneStep(void* _cmd);
  virtual void FirstVisit();
  virtual void LastVisit();
  virtual bool EndOfPhase();

  virtual void CtrlInitialization(const std::string & setting_file_name);

  void setTransitionTime(double time){ end_time_ = time; }
  void setStanceHeight(double height) {
    des_base_height_ = height;
    b_set_height_target_ = true;
  }

protected:
  bool b_set_height_target_;
  double des_base_height_;
  double ini_base_height_;
    int dim_contact_;

  double end_time_;
  int moving_foot_;
  bool b_increase_; // Increasing or decreasing reaction force
  double max_rf_z_;
  double min_rf_z_;
 
  KinWBC* kin_wbc_;
  Task* base_task_;
  WBLC_ContactSpec* rfoot_contact_;
  WBLC_ContactSpec* lfoot_contact_;
  WBLC* wblc_;
  WBLC_ExtraData* wblc_data_;

  dynacore::Vector des_jpos_;
  dynacore::Vector des_jvel_;
  dynacore::Vector des_jacc_;
  
  dynacore::Vector Kp_;
  dynacore::Vector Kd_;

  void _task_setup();
  void _contact_setup();
  void _compute_torque_wblc(dynacore::Vector & gamma);

  Mercury_StateProvider* sp_;
  double ctrl_start_time_;
};
#endif
