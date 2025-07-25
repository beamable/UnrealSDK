
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeamoV2PromoteBeamoManifestRequestBody.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#include "PostManifestsPromoteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostManifestsPromoteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeamoV2PromoteBeamoManifestRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostManifestsPromoteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostManifestsPromote",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostManifestsPromoteRequest* Make(FString _SourceRealmId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestsPromoteSuccess, FBeamRequestContext, Context, UPostManifestsPromoteRequest*, Request, UBeamoV2EmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestsPromoteError, FBeamRequestContext, Context, UPostManifestsPromoteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostManifestsPromoteComplete, FBeamRequestContext, Context, UPostManifestsPromoteRequest*, Request);

using FPostManifestsPromoteFullResponse = FBeamFullResponse<UPostManifestsPromoteRequest*, UBeamoV2EmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPostManifestsPromoteFullResponse, FPostManifestsPromoteFullResponse);
