open EditorType;

open AssetNodeType;

let getTextureNodeMap = editorState =>
  editorState.assetRecord |> TextureNodeMapAssetService.getTextureNodeMap;

let setTextureNodeMap = (textureNodeMap, editorState) => {
  ...editorState,
  assetRecord:
    editorState.assetRecord
    |> TextureNodeMapAssetService.setTextureNodeMap(textureNodeMap),
};

let setResult = (nodeId, result, editorState) => {
  ...editorState,
  assetRecord:
    editorState.assetRecord
    |> TextureNodeMapAssetService.setResult(nodeId, result),
};

let getTextureParentId = (currentNodeId, textureNodeMap) =>
  textureNodeMap
  |> WonderCommonlib.SparseMapService.unsafeGet(currentNodeId)
  |> (({parentId}: textureResultType) => parentId);

let buildTextureNodeResult = (textureIndex, parentId, imageId) => {
  textureIndex,
  parentId,
  imageId,
};

let setTextureNodeResultParent = (parentId, texureResult: textureResultType) => {
  ...texureResult,
  parentId,
};