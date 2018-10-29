open Js.Promise;

/* let testImportTexture =
     (
       ~sandbox,
       ~buildAssetTreeRootFunc,
       ~testFunc,
       ~fileCallCount=ExportPackageTool.getFetchPackageContentWithoutAssetCount(),
       (),
     ) =>
   Js.Promise.(
     ExportPackageTool.getAssetJson(
       ~sandbox,
       ~buildAssetTreeRootFunc,
       ~testFunc=
         ((assetTreeData, assetJson)) => {
           StateEditorService.getState()
           |> AssetTreeEditorService.deepDisposeAssetTreeRoot
           |> StateEditorService.setState
           |> ignore;

           assetJson
           |> HeaderImportUtils._handleImportJson("Assets.json")
           |> then_(editorState =>
                testFunc(assetTreeData, editorState) |> resolve
              );
         },
       (),
     )
   ); */

let testImportPackage = (~testFunc, ()) => {
  let wpkArrayBuffer = ExportPackageTool.exportWPK();

  HeaderImportPackageUtils._import(wpkArrayBuffer |> Obj.magic)
  |> WonderBsMost.Most.drain
  |> then_(_ => testFunc());
};

let getImportedMaterialAssetResults = () =>
  AssetMaterialNodeMapEditorService.getResults
  |> StateLogicService.getEditorState;

let getFirstImportedMaterialAssetData = () => {
  let (materialNodeId, {materialComponent}: AssetNodeType.materialResultType) =
    getImportedMaterialAssetResults() |> ArrayService.unsafeGetFirst;

  (materialNodeId, materialComponent);
};

let getImporteMaterialAssetMaterialComponents = () =>
  AssetMaterialNodeMapEditorService.getValidValues
  |> StateLogicService.getEditorState
  |> Js.Array.map(({materialComponent}: AssetNodeType.materialResultType) =>
       materialComponent
     );

let getImporteMaterialAssetBasicMaterialComponents = () =>
  AssetMaterialNodeMapEditorService.getValidValues
  |> StateLogicService.getEditorState
  |> Js.Array.filter(({type_}: AssetNodeType.materialResultType) =>
       type_ === AssetMaterialDataType.BasicMaterial
     )
  |> Js.Array.map(({materialComponent}: AssetNodeType.materialResultType) =>
       materialComponent
     );

let getImporteMaterialAssetLightMaterialComponents = () =>
  AssetMaterialNodeMapEditorService.getValidValues
  |> StateLogicService.getEditorState
  |> Js.Array.filter(({type_}: AssetNodeType.materialResultType) =>
       type_ === AssetMaterialDataType.LightMaterial
     )
  |> Js.Array.map(({materialComponent}: AssetNodeType.materialResultType) =>
       materialComponent
     );

let getImportedTextureAssetTextureComponents = () =>
  AssetTextureNodeMapEditorService.getValidValues
  |> StateLogicService.getEditorState
  |> Js.Array.map(({textureComponent}: AssetNodeType.textureResultType) =>
       textureComponent
     );

let getImportedWDBAssetData = () =>
  StateEditorService.getState()
  |> AssetWDBNodeMapEditorService.getWDBNodeMap
  |> SparseMapService.getValidDataArr;

let getFirstImportedWDBAssetData = () =>
  getImportedWDBAssetData() |> ArrayService.unsafeGetFirst;