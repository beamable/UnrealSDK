
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/AccountsBasicAccount.h"

#include "GetFindRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetFindRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query", Category="Beam")
	FString Query = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetFindRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make GetFind",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetFindRequest* Make(FString _Query, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFindSuccess, FBeamRequestContext, Context, UGetFindRequest*, Request, UAccountsBasicAccount*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFindError, FBeamRequestContext, Context, UGetFindRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetFindComplete, FBeamRequestContext, Context, UGetFindRequest*, Request);

using FGetFindFullResponse = FBeamFullResponse<UGetFindRequest*, UAccountsBasicAccount*>;
DECLARE_DELEGATE_OneParam(FOnGetFindFullResponse, FGetFindFullResponse);
