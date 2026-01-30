
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Party.h"

#include "PutPartiesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutPartiesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UParty* Body = {};

	// Beam Base Request Declaration
	UPutPartiesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", DisplayName="Make PutParties",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Id,_Restriction,_Leader,_MaxSize,_Created,_Members,_PendingInvites,_MembersTags,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutPartiesRequest* Make(FOptionalString _Id, FOptionalString _Restriction, FOptionalBeamGamerTag _Leader, FOptionalInt32 _MaxSize, FOptionalDateTime _Created, FOptionalArrayOfBeamGamerTag _Members, FOptionalArrayOfString _PendingInvites, FOptionalMapOfTagList _MembersTags, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPartiesSuccess, FBeamRequestContext, Context, UPutPartiesRequest*, Request, UParty*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPartiesError, FBeamRequestContext, Context, UPutPartiesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutPartiesComplete, FBeamRequestContext, Context, UPutPartiesRequest*, Request);

using FPutPartiesFullResponse = FBeamFullResponse<UPutPartiesRequest*, UParty*>;
DECLARE_DELEGATE_OneParam(FOnPutPartiesFullResponse, FPutPartiesFullResponse);
