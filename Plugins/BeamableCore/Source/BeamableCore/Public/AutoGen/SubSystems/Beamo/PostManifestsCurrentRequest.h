
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#include "PostManifestsCurrentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostManifestsCurrentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UPostManifestsCurrentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostManifestsCurrent",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostManifestsCurrentRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestsCurrentSuccess, FBeamRequestContext, Context, UPostManifestsCurrentRequest*, Request, UBeamoV2EmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestsCurrentError, FBeamRequestContext, Context, UPostManifestsCurrentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostManifestsCurrentComplete, FBeamRequestContext, Context, UPostManifestsCurrentRequest*, Request);

using FPostManifestsCurrentFullResponse = FBeamFullResponse<UPostManifestsCurrentRequest*, UBeamoV2EmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPostManifestsCurrentFullResponse, FPostManifestsCurrentFullResponse);
