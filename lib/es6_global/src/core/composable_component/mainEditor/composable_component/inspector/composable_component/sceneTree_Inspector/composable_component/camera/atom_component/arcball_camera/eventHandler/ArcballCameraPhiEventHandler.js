

import * as EventHandler$WonderEditor from "../../../../../../../../../../../ui/eventHandler/EventHandler.js";
import * as EmptyEventHandler$WonderEditor from "../../../../../../../../../../../ui/eventHandler/EmptyEventHandler.js";
import * as StateEngineService$WonderEditor from "../../../../../../../../../../../../service/state/engine/state/StateEngineService.js";
import * as ArcballCameraEngineService$WonderEditor from "../../../../../../../../../../../../service/state/engine/ArcballCameraEngineService.js";

function setUndoValueToCopiedEngineState(param, arcballCameraController, phi) {
  return ArcballCameraEngineService$WonderEditor.setArcballCameraControllerPhi(arcballCameraController, phi, StateEngineService$WonderEditor.deepCopyForRestore(StateEngineService$WonderEditor.unsafeGetState(/* () */0)));
}

var CustomEventHandler_000 = /* handleSelfLogic */EmptyEventHandler$WonderEditor.EmptyEventHandler[0];

var CustomEventHandler = /* module */[
  CustomEventHandler_000,
  /* setUndoValueToCopiedEngineState */setUndoValueToCopiedEngineState
];

var MakeEventHandler = EventHandler$WonderEditor.MakeEventHandler(CustomEventHandler);

export {
  CustomEventHandler ,
  MakeEventHandler ,
  
}
/* MakeEventHandler Not a pure module */
