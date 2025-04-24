
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetStatusResponse.h"

#include "BasicBeamoGetStatusRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicBeamoGetStatusRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicBeamoGetStatusRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BasicBeamoGetStatus",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicBeamoGetStatusRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoGetStatusSuccess, FBeamRequestContext, Context, UBasicBeamoGetStatusRequest*, Request, UGetStatusResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoGetStatusError, FBeamRequestContext, Context, UBasicBeamoGetStatusRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicBeamoGetStatusComplete, FBeamRequestContext, Context, UBasicBeamoGetStatusRequest*, Request);

using FBasicBeamoGetStatusFullResponse = FBeamFullResponse<UBasicBeamoGetStatusRequest*, UGetStatusResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicBeamoGetStatusFullResponse, FBasicBeamoGetStatusFullResponse);
