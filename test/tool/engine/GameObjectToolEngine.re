let createGameObject = state => {
  open Wonderjs;

  let (state, gameObject) = GameObjectAPI.createGameObject(state);
  (
    state,
    gameObject,
    GameObjectAPI.unsafeGetGameObjectTransformComponent(gameObject, state),
  );
};

let getAllArcballCameraControllers = (gameObject, engineState) =>
  GameObjectEngineService.getAllGameObjects(gameObject, engineState)
  |> Js.Array.filter(gameObject =>
       GameObjectComponentEngineService.hasArcballCameraControllerComponent(
         gameObject,
         engineState,
       )
     )
  |> Js.Array.map(gameObject =>
       GameObjectComponentEngineService.unsafeGetArcballCameraControllerComponent(
         gameObject,
         engineState,
       )
     );

let getAllPointLightGameObjects = (gameObject, engineState) =>
  GameObjectEngineService.getAllGameObjects(gameObject, engineState)
  |> Js.Array.filter(gameObject =>
       GameObjectComponentEngineService.hasPointLightComponent(
         gameObject,
         engineState,
       )
     );
/* |> Js.Array.map(gameObject =>
     GameObjectComponentEngineService.unsafeGetPointLightComponent(
       gameObject,
       engineState,
     )
   ); */

let disposeAllGameObjects = (gameObject, engineState) =>
  GameObjectEngineService.getAllGameObjects(gameObject, engineState)
  |> WonderCommonlib.ArrayService.reduceOneParam(
       (. engineState, gameObject) =>
         engineState |> GameObjectEngineService.disposeGameObject(gameObject),
       engineState,
     );