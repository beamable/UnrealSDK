
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/SendMessageRequestBody.h"
#include "AutoGen/SendMessageResponse.h"

#include "PostMessagesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostMessagesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	USendMessageRequestBody* Body;

	// Beam Base Request Declaration
	UPostMessagesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostMessagesRequest* MakePostMessagesRequest(int64 _ObjectId, FString _RoomId, FString _Content, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMessagesSuccess, FBeamRequestContext, Context, UPostMessagesRequest*, Request, USendMessageResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMessagesError, FBeamRequestContext, Context, UPostMessagesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostMessagesComplete, FBeamRequestContext, Context, UPostMessagesRequest*, Request);

using FPostMessagesFullResponse = FBeamFullResponse<UPostMessagesRequest*, USendMessageResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostMessagesFullResponse, FPostMessagesFullResponse);
