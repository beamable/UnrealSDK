
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SearchExtendedRequestBody.h"
#include "BeamableCore/Public/AutoGen/SearchExtendedResponse.h"

#include "PostSearchExtendedRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSearchExtendedRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USearchExtendedRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostSearchExtendedRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make PostSearchExtended",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostSearchExtendedRequest* Make(FString _Domain, FString _ObjectType, FString _Access, TArray<UStatsSearchCriteria*> _Criteria, TArray<FString> _StatKeys, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSearchExtendedSuccess, FBeamRequestContext, Context, UPostSearchExtendedRequest*, Request, USearchExtendedResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSearchExtendedError, FBeamRequestContext, Context, UPostSearchExtendedRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSearchExtendedComplete, FBeamRequestContext, Context, UPostSearchExtendedRequest*, Request);

using FPostSearchExtendedFullResponse = FBeamFullResponse<UPostSearchExtendedRequest*, USearchExtendedResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSearchExtendedFullResponse, FPostSearchExtendedFullResponse);
