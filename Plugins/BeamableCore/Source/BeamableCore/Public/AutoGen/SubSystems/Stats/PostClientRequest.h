
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamStatsType.h"
#include "BeamableCore/Public/AutoGen/StatUpdateRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PostClientRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostClientRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamStatsType ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStatUpdateRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostClientRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make PostClient",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bEmitAnalytics,Body_ObjectId,_Set,_Add,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostClientRequest* Make(FBeamStatsType _ObjectId, FOptionalBool _bEmitAnalytics, FOptionalBeamStatsType Body_ObjectId, FOptionalMapOfString _Set, FOptionalMapOfString _Add, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostClientSuccess, FBeamRequestContext, Context, UPostClientRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostClientError, FBeamRequestContext, Context, UPostClientRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostClientComplete, FBeamRequestContext, Context, UPostClientRequest*, Request);

using FPostClientFullResponse = FBeamFullResponse<UPostClientRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostClientFullResponse, FPostClientFullResponse);
