module Method = {
  let _blurArcballCameraValue =
      (
        (uiState, dispatchFunc),
        arcballCameraController,
        value,
        (
          unsafeGetArcballCameraControllerValueFunc,
          pushUndoStackWithCopiedEngineStateFunc,
        ),
      ) =>
    unsafeGetArcballCameraControllerValueFunc(arcballCameraController)
    |> StateLogicService.getEngineStateToGetData
    |> ValueService.isValueEqual(ValueType.Float, value) ?
      () :
      pushUndoStackWithCopiedEngineStateFunc(
        (uiState, dispatchFunc),
        arcballCameraController,
        value,
      );
  /* TransformUtils.refreshTransformWithDispatchFunc(dispatchFunc)
     |> StateLogicService.getAndSetState; */

  let _blurArcballCameraTarget =
      (
        (uiState, dispatchFunc),
        arcballCameraController,
        target,
        (
          unsafeGetArcballCameraControllerTargetFunc,
          pushUndoStackWithCopiedEngineStateFunc,
        ),
      ) => {
    let newTarget =
      unsafeGetArcballCameraControllerTargetFunc(arcballCameraController)
      |> StateLogicService.getEngineStateToGetData;

    Vector3Service.isEqual(target, newTarget) ?
      () :
      pushUndoStackWithCopiedEngineStateFunc(
        (uiState, dispatchFunc),
        arcballCameraController,
        target,
      );
    /* TransformUtils.refreshTransformWithDispatchFunc(dispatchFunc)
       |> StateLogicService.getAndSetState; */
  };

  let blurArcballCameraDistance =
      ((uiState, dispatchFunc), arcballCameraController, distance) =>
    _blurArcballCameraValue(
      (uiState, dispatchFunc),
      arcballCameraController,
      distance,
      (
        ArcballCameraEngineService.unsafeGetArcballCameraControllerDistance,
        ArcballCameraDistanceEventHandler.MakeEventHandler.pushUndoStackWithCopiedEngineState,
      ),
    );

  let blurArcballCameraMinDistance =
      ((uiState, dispatchFunc), arcballCameraController, minDistance) =>
    _blurArcballCameraValue(
      (uiState, dispatchFunc),
      arcballCameraController,
      minDistance,
      (
        ArcballCameraEngineService.unsafeGetArcballCameraControllerMinDistance,
        ArcballCameraMinDistanceEventHandler.MakeEventHandler.pushUndoStackWithCopiedEngineState,
      ),
    );

  let blurArcballCameraPhi =
      ((uiState, dispatchFunc), arcballCameraController, minDistance) =>
    _blurArcballCameraValue(
      (uiState, dispatchFunc),
      arcballCameraController,
      minDistance,
      (
        ArcballCameraEngineService.unsafeGetArcballCameraControllerPhi,
        ArcballCameraPhiEventHandler.MakeEventHandler.pushUndoStackWithCopiedEngineState,
      ),
    );

  let blurArcballCameraTheta =
      ((uiState, dispatchFunc), arcballCameraController, minDistance) =>
    _blurArcballCameraValue(
      (uiState, dispatchFunc),
      arcballCameraController,
      minDistance,
      (
        ArcballCameraEngineService.unsafeGetArcballCameraControllerTheta,
        ArcballCameraThetaEventHandler.MakeEventHandler.pushUndoStackWithCopiedEngineState,
      ),
    );

  let blurArcballCameraTarget =
      ((uiState, dispatchFunc), arcballCameraController, target) =>
    _blurArcballCameraTarget(
      (uiState, dispatchFunc),
      arcballCameraController,
      target,
      (
        ArcballCameraEngineService.unsafeGetArcballCameraControllerTarget,
        ArcballCameraTargetEventHandler.MakeEventHandler.pushUndoStackWithCopiedEngineState,
      ),
    );

  let dragDropArcballCameraDistance =
      ((uiState, dispatchFunc), arcballCameraController, distance) => {
    blurArcballCameraDistance(
      (uiState, dispatchFunc),
      arcballCameraController,
      distance,
    );

    TransformUtils.refreshTransformWithDispatchFunc(dispatchFunc)
    |> StateLogicService.getAndSetState;
  };

  let changeDistance = (arcballCameraController, value) =>
    ArcballCameraEngineService.setArcballCameraControllerDistance(
      value,
      arcballCameraController,
    )
    |> StateLogicService.getAndRefreshEngineStateWithFunc;

  let changeMinDistance = (arcballCameraController, value) =>
    ArcballCameraEngineService.setArcballCameraControllerMinDistance(
      value,
      arcballCameraController,
    )
    |> StateLogicService.getAndRefreshEngineStateWithFunc;

  let changePhi = (arcballCameraController, value) =>
    ArcballCameraEngineService.setArcballCameraControllerPhi(
      arcballCameraController,
      value,
    )
    |> StateLogicService.getAndRefreshEngineStateWithFunc;

  let changeTheta = (arcballCameraController, value) =>
    ArcballCameraEngineService.setArcballCameraControllerTheta(
      arcballCameraController,
      value,
    )
    |> StateLogicService.getAndRefreshEngineStateWithFunc;

  let _setTarget = (arcballCameraController, target) =>
    ArcballCameraEngineService.setArcballCameraControllerTarget(
      arcballCameraController,
      target,
    )
    |> StateLogicService.getAndRefreshEngineStateWithFunc;

  let changeTargetX = (arcballCameraController, value) => {
    let (_x, y, z) =
      ArcballCameraEngineService.unsafeGetArcballCameraControllerTarget(
        arcballCameraController,
      )
      |> StateLogicService.getEngineStateToGetData;

    _setTarget(arcballCameraController, (value, y, z));
  };

  let changeTargetY = (arcballCameraController, value) => {
    let (x, _y, z) =
      ArcballCameraEngineService.unsafeGetArcballCameraControllerTarget(
        arcballCameraController,
      )
      |> StateLogicService.getEngineStateToGetData;

    _setTarget(arcballCameraController, (x, value, z));
  };

  let changeTargetZ = (arcballCameraController, value) => {
    let (x, y, _z) =
      ArcballCameraEngineService.unsafeGetArcballCameraControllerTarget(
        arcballCameraController,
      )
      |> StateLogicService.getEngineStateToGetData;

    _setTarget(arcballCameraController, (x, y, value));
  };

  let renderDistanceField =
      ((uiState, dispatchFunc) as uiStoreDataTuple, arcballCameraController) =>
    <MainEditorFloatInputBaseComponent
      label="Distance"
      getComponentValueFunc=(
        ArcballCameraEngineService.unsafeGetArcballCameraControllerDistance(
          arcballCameraController,
        )
      )
      changeComponentValueFunc=(changeDistance(arcballCameraController))
      blurValueFunc=(
        blurArcballCameraDistance(uiStoreDataTuple, arcballCameraController)
      )
      dragDropFunc=(
        value =>
          dragDropArcballCameraDistance(
            uiStoreDataTuple,
            arcballCameraController,
            value,
          )
      )
    />;

  let renderMinDistanceField =
      ((uiState, dispatchFunc) as uiStoreDataTuple, arcballCameraController) =>
    <MainEditorFloatInputBaseComponent
      label="Min Distance"
      getComponentValueFunc=(
        ArcballCameraEngineService.unsafeGetArcballCameraControllerMinDistance(
          arcballCameraController,
        )
      )
      changeComponentValueFunc=(changeMinDistance(arcballCameraController))
      blurValueFunc=(
        blurArcballCameraMinDistance(
          uiStoreDataTuple,
          arcballCameraController,
        )
      )
      dragDropFunc=(
        value => {
          blurArcballCameraMinDistance(
            uiStoreDataTuple,
            arcballCameraController,
            value,
          );

          TransformUtils.refreshTransformWithDispatchFunc(dispatchFunc)
          |> StateLogicService.getAndSetState;
        }
      )
    />;

  let renderTargetField = ((uiState, dispatchFunc), arcballCameraController) =>
    <ThreeFloatInput
      uiState
      dispatchFunc
      label="Target"
      gameObjectComponent=arcballCameraController
      changeXFunc=changeTargetX
      changeYFunc=changeTargetY
      changeZFunc=changeTargetZ
      getDataFunc=ArcballCameraEngineService.unsafeGetArcballCameraControllerTarget
      blurEventFunc=blurArcballCameraTarget
      dragDropFunc=(
        ((uiState, dispatchFunc), arcballCameraController, target) => {
          blurArcballCameraTarget(
            (uiState, dispatchFunc),
            arcballCameraController,
            target,
          );

          TransformUtils.refreshTransformWithDispatchFunc(dispatchFunc)
          |> StateLogicService.getAndSetState;
        }
      )
      canBeZero=true
    />;

  let renderPhiField =
      ((uiState, dispatchFunc) as uiStoreDataTuple, arcballCameraController) =>
    <MainEditorFloatInputBaseComponent
      label="Phi"
      getComponentValueFunc=(
        ArcballCameraEngineService.unsafeGetArcballCameraControllerPhi(
          arcballCameraController,
        )
      )
      changeComponentValueFunc=(changePhi(arcballCameraController))
      blurValueFunc=(
        blurArcballCameraPhi(uiStoreDataTuple, arcballCameraController)
      )
      dragDropFunc=(
        value => {
          blurArcballCameraPhi(
            uiStoreDataTuple,
            arcballCameraController,
            value,
          );

          TransformUtils.refreshTransformWithDispatchFunc(dispatchFunc)
          |> StateLogicService.getAndSetState;
        }
      )
    />;

  let renderThetaField =
      ((uiState, dispatchFunc) as uiStoreDataTuple, arcballCameraController) =>
    <MainEditorFloatInputBaseComponent
      label="Theta"
      getComponentValueFunc=(
        ArcballCameraEngineService.unsafeGetArcballCameraControllerTheta(
          arcballCameraController,
        )
      )
      changeComponentValueFunc=(changeTheta(arcballCameraController))
      blurValueFunc=(
        blurArcballCameraTheta(uiStoreDataTuple, arcballCameraController)
      )
      dragDropFunc=(
        value => {
          blurArcballCameraTheta(
            uiStoreDataTuple,
            arcballCameraController,
            value,
          );

          TransformUtils.refreshTransformWithDispatchFunc(dispatchFunc)
          |> StateLogicService.getAndSetState;
        }
      )
    />;
};

let component =
  ReasonReact.statelessComponent("MainEditorArcballCameraController");

let render =
    (
      (uiState, dispatchFunc) as uiStoreDataTuple,
      arcballCameraController,
      _self,
    ) =>
  <article className="wonder-inspector-arcballCameraController">
    (Method.renderDistanceField(uiStoreDataTuple, arcballCameraController))
    (Method.renderMinDistanceField(uiStoreDataTuple, arcballCameraController))
    (Method.renderTargetField(uiStoreDataTuple, arcballCameraController))
    (Method.renderPhiField(uiStoreDataTuple, arcballCameraController))
    (Method.renderThetaField(uiStoreDataTuple, arcballCameraController))
  </article>;

let make = (~uiState, ~dispatchFunc, ~arcballCameraController, _children) => {
  ...component,
  render: self =>
    render((uiState, dispatchFunc), arcballCameraController, self),
};