#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include <QString>
#include "ITP_Interface.h"

QString mergeRobTarget(ITP_RobTarget P); //合并
QString mergeRobTarget_Pose(ITP_Pos Pose);
QString mergeRobTarget_Orient(ITP_Orient Orient);
QString mergeRobTarget_ConfData(ITP_ConfData ConfData);
QString mergeRobTarget_ExtJoint(ITP_ExtJoint ExtJoint);


QString mergeJointTarget(ITP_JointTarget J); //合并
QString mergeJointTarget_RobJoint(ITP_RobJoint robax);
QString mergeJointTarget_ExtJoint(ITP_ExtJoint extax);

QString mergeWobjData(ITP_WobjData W); //合并
QString mergeWobjData_Uframe(ITP_Pose Uframe);
QString mergeWobjData_Pose(ITP_Pos Pose);
QString mergeWobjData_Orient(ITP_Orient Orient);

QString mergeToolData(ITP_ToolData T); //合并
QString mergeTobjData_tframe(ITP_Pose tframe);
QString mergeToolData_Pos(ITP_Pos Pose);
QString mergeToolData_Orient(ITP_Orient Orient);

QString mergeZoneData(ITP_ZoneData Z); //合并
QString mergeZoneData_StopPointData(ITP_StopPointData inpos);
QString mergeZoneData_ZoneDistanceData(ITP_ZoneDistanceData bgnzone);

QString mergeSpeed(ITP_SpeedData V); //合并

QString DoubleToString(double value); //自定义将double转成char*


#endif // DATAPROCESS_H
