// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Content/BeamContentHooks.h"

bool UBeamContentHooks::ContentFilter_Implementation(UBeamIndividualContentDownloadData* BeamContent)
{
	return true;
}

void UBeamContentHooks::OnLoadBeamContent_Implementation(UBeamIndividualContentDownloadData* BeamContent)
{
}
