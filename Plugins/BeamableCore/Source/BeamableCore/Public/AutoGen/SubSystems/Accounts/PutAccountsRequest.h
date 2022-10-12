
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/AccountUpdate.h"
#include "AutoGen/AccountsObjectAccount.h"

#include "PutAccountsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAccountsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UAccountUpdate* Body;

	// Beam Base Request Declaration
	UPutAccountsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_ThirdParty,_Country,_Language,_GamerTagAssoc,_Token,_DeviceId,_UserName,Outer"))
	static UPutAccountsRequest* MakePutAccountsRequest(int64 _ObjectId, FOptionalString _ThirdParty, bool _bHasThirdPartyToken, FOptionalString _Country, FOptionalString _Language, FOptionalGamerTagAssociation _GamerTagAssoc, FOptionalString _Token, FOptionalString _DeviceId, FOptionalString _UserName, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAccountsSuccess, FBeamRequestContext, Context, UPutAccountsRequest*, Request, UAccountsObjectAccount*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAccountsError, FBeamRequestContext, Context, UPutAccountsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAccountsComplete, FBeamRequestContext, Context, UPutAccountsRequest*, Request);

using FPutAccountsFullResponse = FBeamFullResponse<UPutAccountsRequest*, UAccountsObjectAccount*>;
DECLARE_DELEGATE_OneParam(FOnPutAccountsFullResponse, FPutAccountsFullResponse);
