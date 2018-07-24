#include "transform.h"


void Transform::CopyFromFbxTransform(const FbxNode * const ptransform)
{
	mPosition.CopyFromFbxDouble3(&ptransform->LclTranslation.Get());
	mRotation.CopyFromFbxDouble3(&ptransform->LclRotation.Get());
	mScale.CopyFromFbxDouble3(&ptransform->LclScaling.Get());
}

void Transform::CopyToFbxTransform(FbxNode * const ptransform)
{
	ptransform->LclTranslation.Set(mPosition.GetFbxDouble3());
	ptransform->LclRotation.Set(mRotation.GetFbxDouble3());
	ptransform->LclScaling.Set(mScale.GetFbxDouble3());
}

void Transform::CopyFromTransformData(const TransformData * const pdata)
{
	mPosition.CopyFromVector3Data(&pdata->mPosition);
	mRotation.CopyFromVector3Data(&pdata->mRotation);
	mScale.CopyFromVector3Data(&pdata->mScale);
}

void Transform::CopyToTransformData(TransformData * const pdata)
{
	mPosition.CopyToVector3Data(&pdata->mPosition);
	mRotation.CopyToVector3Data(&pdata->mRotation);
	mScale.CopyToVector3Data(&pdata->mScale);
}

TransformData Transform::GetTransformData()
{
	TransformData data;
	CopyToTransformData(&data);
	return data;
}