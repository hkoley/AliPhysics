///////////////////////////////////////////////////////////////////
//
// AddTaskWHMult                                                               //            
// Author: T. Kawagichi Univ. of Tsukuba                            //
//                                                               //
///////////////////////////////////////////////////////////////////

class AliAnalysisDataContainer;

AliAnalysisTaskWHMult* AddTaskWHMult(
   TString name = "name",
   Bool_t flagEG1 = kTRUE
  )
{

    // get the manager via the static access member. since it's static, you don't need
    // an instance of the class to call the function
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
        return 0x0;
    }
    // get the input event handler, again via a static method. 
    // this handler is part of the managing system and feeds events
    // to your task
    if (!mgr->GetInputEventHandler()) {
        return 0x0;
    }


    // by default, a file is open for writing. here, we get the filename
    TString fileName = AliAnalysisManager::GetCommonFileName();
    fileName += ":CalWh";      // create a subfolder in the file
    // now we create an instance of your task
    AliAnalysisTaskWHMult* task = new AliAnalysisTaskWHMult(name.Data());   
    task->SetEG1(flagEG1);

    if(!task) return 0x0;

    // add your task to the manager
    mgr->AddTask(task);

    TString containerName = mgr->GetCommonFileName();
    containerName += ":PWGHF_CalWh";
    TString SubcontainerName = Form("CalWh");
    SubcontainerName += name;
    AliAnalysisDataContainer *cinput  = mgr->GetCommonInputContainer();
    AliAnalysisDataContainer *coutput1 = mgr->CreateContainer(SubcontainerName, TList::Class(),AliAnalysisManager::kOutputContainer, containerName.Data());
    mgr->ConnectInput(task, 0, cinput);
    mgr->ConnectOutput(task, 1, coutput1); 

    return task;

}
