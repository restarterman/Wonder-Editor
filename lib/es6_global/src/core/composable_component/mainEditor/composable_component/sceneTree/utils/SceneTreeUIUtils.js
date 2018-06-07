

import * as OptionService$WonderEditor from "../../../../../../service/primitive/OptionService.js";

function getFlag() {
  return "sceneTree";
}

function unsafeGetSceneGraphDataFromStore(store) {
  return OptionService$WonderEditor.unsafeGet(store[/* sceneTreeState */3][/* sceneGraphData */0]);
}

export {
  getFlag ,
  unsafeGetSceneGraphDataFromStore ,
  
}
/* OptionService-WonderEditor Not a pure module */