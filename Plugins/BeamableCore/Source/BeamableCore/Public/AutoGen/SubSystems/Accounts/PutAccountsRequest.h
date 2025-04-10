
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamableCore/Public/AutoGen/AccountUpdate.h"
#include "BeamableCore/Public/AutoGen/AccountsObjectAccount.h"

#include "PutAccountsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAccountsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamAccountId ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAccountUpdate* Body = {};

	// Beam Base Request Declaration
	UPutAccountsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PutAccounts",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ThirdParty,_Country,_Language,_GamerTagAssoc,_Token,_DeviceId,_UserName,_External,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutAccountsRequest* Make(FBeamAccountId _ObjectId, bool _bHasThirdPartyToken, FOptionalString _ThirdParty, FOptionalString _Country, FOptionalString _Language, FOptionalGamerTagAssociation _GamerTagAssoc, FOptionalString _Token, FOptionalString _DeviceId, FOptionalString _UserName, FOptionalArrayOfBeamExternalIdentity _External, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAccountsSuccess, FBeamRequestContext, Context, UPutAccountsRequest*, Request, UAccountsObjectAccount*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAccountsError, FBeamRequestContext, Context, UPutAccountsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAccountsComplete, FBeamRequestContext, Context, UPutAccountsRequest*, Request);

using FPutAccountsFullResponse = FBeamFullResponse<UPutAccountsRequest*, UAccountsObjectAccount*>;
DECLARE_DELEGATE_OneParam(FOnPutAccountsFullResponse, FPutAccountsFullResponse);
