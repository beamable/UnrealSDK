
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ApiBeamoOtelViewsDeleteBeamoOtelResponse.h"

#include "DeleteOtelViewsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteOtelViewsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="View Id", Category="Beam")
	FString ViewId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeleteOtelViewsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make DeleteOtelViews",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteOtelViewsRequest* Make(FString _ViewId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteOtelViewsSuccess, FBeamRequestContext, Context, UDeleteOtelViewsRequest*, Request, UApiBeamoOtelViewsDeleteBeamoOtelResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteOtelViewsError, FBeamRequestContext, Context, UDeleteOtelViewsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteOtelViewsComplete, FBeamRequestContext, Context, UDeleteOtelViewsRequest*, Request);

using FDeleteOtelViewsFullResponse = FBeamFullResponse<UDeleteOtelViewsRequest*, UApiBeamoOtelViewsDeleteBeamoOtelResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteOtelViewsFullResponse, FDeleteOtelViewsFullResponse);
