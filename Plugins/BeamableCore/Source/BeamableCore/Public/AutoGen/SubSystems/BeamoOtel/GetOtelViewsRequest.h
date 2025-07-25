
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/OtelViewsResponse.h"

#include "GetOtelViewsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetOtelViewsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FOptionalString PlayerId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetOtelViewsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make GetOtelViews",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetOtelViewsRequest* Make(FOptionalString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetOtelViewsSuccess, FBeamRequestContext, Context, UGetOtelViewsRequest*, Request, UOtelViewsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetOtelViewsError, FBeamRequestContext, Context, UGetOtelViewsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetOtelViewsComplete, FBeamRequestContext, Context, UGetOtelViewsRequest*, Request);

using FGetOtelViewsFullResponse = FBeamFullResponse<UGetOtelViewsRequest*, UOtelViewsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetOtelViewsFullResponse, FGetOtelViewsFullResponse);
