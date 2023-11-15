
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/UpdateParty.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#include "ApiPartyPutMetadataRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiPartyPutMetadataRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdateParty* Body = {};

	// Beam Base Request Declaration
	UApiPartyPutMetadataRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Party", DisplayName="Beam - Make ApiPartyPutMetadata",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Restriction,_MaxSize,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiPartyPutMetadataRequest* Make(FGuid _Id, FOptionalString _Restriction, FOptionalInt32 _MaxSize, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPartyPutMetadataSuccess, FBeamRequestContext, Context, UApiPartyPutMetadataRequest*, Request, UParty*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPartyPutMetadataError, FBeamRequestContext, Context, UApiPartyPutMetadataRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiPartyPutMetadataComplete, FBeamRequestContext, Context, UApiPartyPutMetadataRequest*, Request);

using FApiPartyPutMetadataFullResponse = FBeamFullResponse<UApiPartyPutMetadataRequest*, UParty*>;
DECLARE_DELEGATE_OneParam(FOnApiPartyPutMetadataFullResponse, FApiPartyPutMetadataFullResponse);
