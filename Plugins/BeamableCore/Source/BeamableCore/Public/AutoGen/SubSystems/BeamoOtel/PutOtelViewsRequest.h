
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/UpdateOtelViewRequestBody.h"
#include "BeamableCore/Public/AutoGen/OtelView.h"

#include "PutOtelViewsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutOtelViewsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="View Id", Category="Beam")
	FString ViewId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdateOtelViewRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutOtelViewsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make PutOtelViews",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bIsFavorite,_bIsPublic,_Name,_Query,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutOtelViewsRequest* Make(FString _ViewId, FOptionalBool _bIsFavorite, FOptionalBool _bIsPublic, FOptionalString _Name, FOptionalString _Query, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutOtelViewsSuccess, FBeamRequestContext, Context, UPutOtelViewsRequest*, Request, UOtelView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutOtelViewsError, FBeamRequestContext, Context, UPutOtelViewsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutOtelViewsComplete, FBeamRequestContext, Context, UPutOtelViewsRequest*, Request);

using FPutOtelViewsFullResponse = FBeamFullResponse<UPutOtelViewsRequest*, UOtelView*>;
DECLARE_DELEGATE_OneParam(FOnPutOtelViewsFullResponse, FPutOtelViewsFullResponse);
