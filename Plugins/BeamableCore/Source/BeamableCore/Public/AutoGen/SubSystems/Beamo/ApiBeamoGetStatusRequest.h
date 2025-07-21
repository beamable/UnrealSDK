
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeamoV2GetStatusResponse.h"

#include "ApiBeamoGetStatusRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiBeamoGetStatusRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiBeamoGetStatusRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ApiBeamoGetStatus",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiBeamoGetStatusRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetStatusSuccess, FBeamRequestContext, Context, UApiBeamoGetStatusRequest*, Request, UBeamoV2GetStatusResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetStatusError, FBeamRequestContext, Context, UApiBeamoGetStatusRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiBeamoGetStatusComplete, FBeamRequestContext, Context, UApiBeamoGetStatusRequest*, Request);

using FApiBeamoGetStatusFullResponse = FBeamFullResponse<UApiBeamoGetStatusRequest*, UBeamoV2GetStatusResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiBeamoGetStatusFullResponse, FApiBeamoGetStatusFullResponse);
