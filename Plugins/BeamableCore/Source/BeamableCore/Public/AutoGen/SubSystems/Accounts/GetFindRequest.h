
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/AccountsBasicAccount.h"

#include "GetFindRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetFindRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query", Category="Beam")
	FString Query;

	// Body Params
	

	// Beam Base Request Declaration
	UGetFindRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Accounts", DisplayName="Beam - Make GetFind",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UGetFindRequest* Make(FString _Query, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFindSuccess, FBeamRequestContext, Context, UGetFindRequest*, Request, UAccountsBasicAccount*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFindError, FBeamRequestContext, Context, UGetFindRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetFindComplete, FBeamRequestContext, Context, UGetFindRequest*, Request);

using FGetFindFullResponse = FBeamFullResponse<UGetFindRequest*, UAccountsBasicAccount*>;
DECLARE_DELEGATE_OneParam(FOnGetFindFullResponse, FGetFindFullResponse);
