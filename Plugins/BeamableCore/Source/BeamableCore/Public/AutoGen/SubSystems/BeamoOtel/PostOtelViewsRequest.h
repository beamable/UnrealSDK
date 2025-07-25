
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/OtelView.h"

#include "PostOtelViewsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostOtelViewsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UOtelView* Body = {};

	// Beam Base Request Declaration
	UPostOtelViewsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make PostOtelViews",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bIsFavorite,_bIsPublic,_Id,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostOtelViewsRequest* Make(FString _PlayerId, FString _Name, FString _Query, FOptionalBool _bIsFavorite, FOptionalBool _bIsPublic, FOptionalObjectId _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostOtelViewsSuccess, FBeamRequestContext, Context, UPostOtelViewsRequest*, Request, UOtelView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostOtelViewsError, FBeamRequestContext, Context, UPostOtelViewsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostOtelViewsComplete, FBeamRequestContext, Context, UPostOtelViewsRequest*, Request);

using FPostOtelViewsFullResponse = FBeamFullResponse<UPostOtelViewsRequest*, UOtelView*>;
DECLARE_DELEGATE_OneParam(FOnPostOtelViewsFullResponse, FPostOtelViewsFullResponse);
