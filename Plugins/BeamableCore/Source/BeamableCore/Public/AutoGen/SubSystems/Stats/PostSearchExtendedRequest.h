
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/SearchExtendedRequestBody.h"
#include "AutoGen/SearchExtendedResponse.h"

#include "PostSearchExtendedRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSearchExtendedRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	USearchExtendedRequestBody* Body;

	// Beam Base Request Declaration
	UPostSearchExtendedRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostSearchExtendedRequest* MakePostSearchExtendedRequest(TArray<UStatsSearchCriteria*> _Criteria, FString _Domain, FString _ObjectType, TArray<FString> _StatKeys, FString _Access, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSearchExtendedSuccess, FBeamRequestContext, Context, UPostSearchExtendedRequest*, Request, USearchExtendedResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSearchExtendedError, FBeamRequestContext, Context, UPostSearchExtendedRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSearchExtendedComplete, FBeamRequestContext, Context, UPostSearchExtendedRequest*, Request);

using FPostSearchExtendedFullResponse = FBeamFullResponse<UPostSearchExtendedRequest*, USearchExtendedResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSearchExtendedFullResponse, FPostSearchExtendedFullResponse);
