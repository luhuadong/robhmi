#include "DataProcess.h"

QString mergeRobTarget(ITP_RobTarget P)
{
    QString Pose;
    QString Orient;
    QString ConfData;
    QString ExtJoint;

    Pose = mergeRobTarget_Pose(P.pose.trans);

    Orient = mergeRobTarget_Orient(P.pose.rot);
    ConfData = mergeRobTarget_ConfData(P.robconf);
    ExtJoint = mergeRobTarget_ExtJoint(P.extax);

    QString String;
    String.sprintf("[%s,%s,%s,%s]",Pose.toLocal8Bit().data(),
                   Orient.toLocal8Bit().data(),ConfData.toLocal8Bit().data(),
                   ExtJoint.toLocal8Bit().data());
    return String;
}

QString mergeRobTarget_Pose(ITP_Pos Pose)
{
    QString String;
    String.sprintf("[%s,%s,%s]",DoubleToString(Pose.x).toLocal8Bit().data(),
                   DoubleToString(Pose.y).toLocal8Bit().data(),DoubleToString(Pose.z).toLocal8Bit().data());
    return String;
}

QString mergeRobTarget_Orient(ITP_Orient Orient)
{
    QString String;
    String.sprintf("[%s,%s,%s,%s]",DoubleToString(Orient.s).toLocal8Bit().data(),
                   DoubleToString(Orient.x).toLocal8Bit().data(),DoubleToString(Orient.y).toLocal8Bit().data(),
                   DoubleToString(Orient.z).toLocal8Bit().data());
    return String;
}

QString mergeRobTarget_ConfData(ITP_ConfData ConfData)
{
    QString String;
    String.sprintf("[%s,%s,%s,%s]",DoubleToString(ConfData.cf1).toLocal8Bit().data(),
                   DoubleToString(ConfData.cf4).toLocal8Bit().data(),DoubleToString(ConfData.cf6).toLocal8Bit().data()
                   ,DoubleToString(ConfData.cfx).toLocal8Bit().data());
    return String;
}

QString mergeRobTarget_ExtJoint(ITP_ExtJoint ExtJoint)
{
    QString String;

    String.append("[");
    for(int i =0;i<6;i++){
        if(i==5)
            String.append(DoubleToString(ExtJoint.eax[i]));
        else
            String.append(DoubleToString(ExtJoint.eax[i])+",");
    }

    String.append("]");

    return String;
}

QString mergeJointTarget(ITP_JointTarget J)
{
    QString String;

    QString robax;
    QString extax;

    robax = mergeJointTarget_RobJoint(J.robax);
    extax = mergeJointTarget_ExtJoint(J.extax);

    String.append("[").append(robax).append(",").append(extax).append("]");

    return String;
}

QString mergeJointTarget_RobJoint(ITP_RobJoint robax)
{
    QString String;

    String.append("[");
    for(int i =0;i<6;i++){
        if(i==5)
            String.append(DoubleToString(robax.rax[i]));
        else
            String.append(DoubleToString(robax.rax[i])+",");
    }

    String.append("]");
    return String;
}

QString mergeJointTarget_ExtJoint(ITP_ExtJoint extax)
{
    QString String;

    String.append("[");
    for(int i =0;i<6;i++){
        if(i==5)
            String.append(DoubleToString(extax.eax[i]));
        else
            String.append(DoubleToString(extax.eax[i])+",");
    }

    String.append("]");
    return String;
}

QString mergeWobjData(ITP_WobjData W)
{
    QString Pose;
    QString Orient;
    Pose = mergeWobjData_Pose(W.uframe.trans);
    Orient = mergeWobjData_Orient(W.uframe.rot);

    QString String;
    QString robhold;
    QString ufprog;

    if(W.robhold=='1')
        robhold="TRUE";
    else
        robhold="FALSE";

    if(W.ufprog=='1')
        ufprog="TRUE";
    else
        ufprog="FALSE";

    String.sprintf("[%s,%s,%s,%s,%s]",robhold.toLocal8Bit().data(),
                   ufprog.toLocal8Bit().data(),W.ufmec,//ufmec.toLocal8Bit().data(),
                   Pose.toLocal8Bit().data(),Orient.toLocal8Bit().data());
    return String;
}

QString mergeWobjData_Pose(ITP_Pos Pose)
{
    QString String;
    String.sprintf("[%s,%s,%s]",DoubleToString(Pose.x).toStdString().data(),
                   DoubleToString(Pose.y).toStdString().data(),DoubleToString(Pose.z).toStdString().data());
    return String;
}

QString mergeWobjData_Orient(ITP_Orient Orient)
{
    QString String;
    String.sprintf("[%s,%s,%s,%s]",DoubleToString(Orient.s).toLocal8Bit().data(),
                   DoubleToString(Orient.x).toLocal8Bit().data(),DoubleToString(Orient.y).toLocal8Bit().data(),
                   DoubleToString(Orient.z).toLocal8Bit().data());
    return String;
}

QString mergeWobjData_Uframe(ITP_Pose Uframe)
{
    QString String;
    QString Pose = mergeWobjData_Pose(Uframe.trans);
    QString Orient = mergeWobjData_Orient(Uframe.rot);

    String.sprintf("[%s,%s]",Pose.toLocal8Bit().data(),Orient.toLocal8Bit().data());
    return String;
}

QString mergeToolData(ITP_ToolData T)
{
    QString String;
    QString Pose;
    QString Orient;
    Pose = mergeToolData_Pos(T.tframe.trans);
    Orient = mergeToolData_Orient(T.tframe.rot);

    QString robhold;
    if(T.robhold == '1')
        robhold = "TRUE";
    else
        robhold = "FALSE";

    String.sprintf("[%s,%s,%s]",robhold.toLocal8Bit().data(),
                   Pose.toLocal8Bit().data(),Orient.toLocal8Bit().data());
    return String;
}

QString mergeToolData_Pos(ITP_Pos Pose)
{
    QString String;
    String.sprintf("[%s,%s,%s]",DoubleToString(Pose.x).toStdString().data(),
                   DoubleToString(Pose.y).toStdString().data(),DoubleToString(Pose.z).toStdString().data());
    return String;
}

QString mergeToolData_Orient(ITP_Orient Orient)
{
    QString String;
    String.sprintf("[%s,%s,%s,%s]",DoubleToString(Orient.s).toLocal8Bit().data(),
                   DoubleToString(Orient.x).toLocal8Bit().data(),DoubleToString(Orient.y).toLocal8Bit().data(),
                   DoubleToString(Orient.z).toLocal8Bit().data());
    return String;
}

QString mergeTobjData_Pose(ITP_Pose tframe)
{
    QString String;
    QString Pose;
    QString Orient;
    Pose = mergeToolData_Pos(tframe.trans);
    Orient = mergeToolData_Orient(tframe.rot);

    String.sprintf("[%s,%s]",Pose.toLocal8Bit().data(),
                   Orient.toLocal8Bit().data());
    return String;
}

QString mergeZoneData(ITP_ZoneData Z)
{
    QString String;
    QString finep;

    if(Z.finep==1){
        finep="TRUE";
        String.sprintf("[%s,%s]",finep.toLocal8Bit().data(),
                       mergeZoneData_StopPointData(Z.inpos).toLocal8Bit().data());
    }else{
        finep="FAlse";
        String.sprintf("[%s,%s]",finep.toLocal8Bit().data(),
                       mergeZoneData_ZoneDistanceData(Z.bgnzone).toLocal8Bit().data());
    }
    return String;
}

QString mergeZoneData_StopPointData(ITP_StopPointData inpos)
{
    QString String;
    String.sprintf("[%d,%d,%s,%s,%s,%s,%s,%s]",inpos.stoppoint,inpos.progsynch,
                   DoubleToString(inpos.inpos.position).toLocal8Bit().data(),
                   DoubleToString(inpos.inpos.speed).toLocal8Bit().data(),
                   DoubleToString(inpos.inpos.mintime).toLocal8Bit().data(),
                   DoubleToString(inpos.inpos.maxtime).toLocal8Bit().data(),
                   DoubleToString(inpos.stoptime).toLocal8Bit().data(),
                   DoubleToString(inpos.followtime).toLocal8Bit().data());
    return String;
}

QString mergeZoneData_ZoneDistanceData(ITP_ZoneDistanceData bgnzone)
{
    QString String;
    String.sprintf("[%s,%s,%s,%s,%s,%s]",DoubleToString(bgnzone.pzone_tcp).toLocal8Bit().data(),
                   DoubleToString(bgnzone.pzone_ori).toLocal8Bit().data(),
                   DoubleToString(bgnzone.pzone_eax).toLocal8Bit().data(),
                   DoubleToString(bgnzone.zone_ori).toLocal8Bit().data(),
                   DoubleToString(bgnzone.zone_leax).toLocal8Bit().data(),
                   DoubleToString(bgnzone.zone_reax).toLocal8Bit().data());
    return String;
}

QString mergeSpeed(ITP_SpeedData V) //合并
{
    char string[256];
    memset(string,0,sizeof(string));

    sprintf(string,"[%s,%s,%s,%s,%s]",DoubleToString(V.time).toLocal8Bit().data(),
            DoubleToString(V.v_tcp).toLocal8Bit().data(),
            DoubleToString(V.v_ort).toLocal8Bit().data(),
            DoubleToString(V.v_leax).toLocal8Bit().data(),
            DoubleToString(V.v_reax).toLocal8Bit().data());

    QString String = QString(string);

    return String;
}

QString DoubleToString(double value) //自定义将double转成char*
{
    QString string;
    string.clear();
    string.sprintf("%f",value);

    QString dot = ".";
    int dotPos= string.indexOf(dot);//查找点的位置

    int i;
    for(i =string.count()-1;i>=dotPos;i--){
        if(string.at(i) == '0'||string.at(i) == '.'){
            string.remove(i,1);
        }else
            break;
    }

    return string;
}
