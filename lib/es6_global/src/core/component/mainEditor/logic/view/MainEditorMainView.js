'use strict';

import * as EditorStateFacade$WonderEditor  from "../../../../../facade/EditorStateFacade.js";
import * as EngineStateFacade$WonderEditor  from "../../../../../facade/EngineStateFacade.js";
import * as MainEditorMainBuss$WonderEditor from "../bussiness/MainEditorMainBuss.js";

function _init(editorState) {
  var engineState = MainEditorMainBuss$WonderEditor.initEngineMain(/* () */0);
  var match = MainEditorMainBuss$WonderEditor.initEditor(/* tuple */[
        editorState,
        engineState
      ]);
  var engineState$1 = MainEditorMainBuss$WonderEditor.initEngineDirector(match[1]);
  return /* tuple */[
          match[0],
          engineState$1
        ];
}

var loopSetState = MainEditorMainBuss$WonderEditor.loopBody;

function _loop() {
  var _loopRequest = function () {
    return requestAnimationFrame((function (time) {
                  var engineState = EngineStateFacade$WonderEditor.getState(/* () */0);
                  EngineStateFacade$WonderEditor.setState(MainEditorMainBuss$WonderEditor.loopBody(time, engineState));
                  _loopRequest(time);
                  return /* () */0;
                }));
  };
  _loopRequest(0);
  return /* () */0;
}

function start() {
  var match = _init(EditorStateFacade$WonderEditor.getState(/* () */0));
  _loop(/* () */0);
  return /* tuple */[
          EditorStateFacade$WonderEditor.setState(match[0]),
          EngineStateFacade$WonderEditor.setState(match[1])
        ];
}

var _initEditor = MainEditorMainBuss$WonderEditor.initEditor;

export {
  _initEditor  ,
  _init        ,
  loopSetState ,
  _loop        ,
  start        ,
  
}
/* EditorStateFacade-WonderEditor Not a pure module */