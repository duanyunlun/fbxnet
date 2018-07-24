#include "geometrytransform.h"

void GeometryTransform::CopyFromFbxTransform(const FbxNode * const ptransform)
{
	mPosition.CopyFromFbxDouble3(&ptransform->GeometricTranslation.Get());
	mRotation.CopyFromFbxDouble3(&ptransform->GeometricRotation.Get());
	mScale.CopyFromFbxDouble3(&ptransform->GeometricScaling.Get());
}

void GeometryTransform::CopyToFbxTransform(FbxNode * const ptransform)
{
	ptransform->GeometricTranslation.Set(mPosition.GetFbxDouble3());
	ptransform->GeometricRotation.Set(mRotation.GetFbxDouble3());
	ptransform->GeometricScaling.Set(mScale.GetFbxDouble3());
}

void GeometryTransform::CopyFromTransformData(const TransformData * const pdata)
{
	mPosition.CopyFromVector3Data(&pdata->mPosition);
	mRotation.CopyFromVector3Data(&pdata->mRotation);
	mScale.CopyFromVector3Data(&pdata->mScale);
}

void GeometryTransform::CopyToTransformData(TransformData * const pdata)
{
	mPosition.CopyToVector3Data(&pdata->mPosition);
	mRotation.CopyToVector3Data(&pdata->mRotation);
	mScale.CopyToVector3Data(&pdata->mScale);
}

TransformData GeometryTransform::GetTransformData()
{
	TransformData data;
	CopyToTransformData(&data);
	return data;
}