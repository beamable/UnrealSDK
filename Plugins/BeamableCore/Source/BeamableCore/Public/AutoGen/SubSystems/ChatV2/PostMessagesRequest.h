
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/SendMessageRequestBody.h"
#include "AutoGen/SendMessageResponse.h"

#include "PostMessagesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostMessagesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USendMessageRequestBody* Body;

	// Beam Base Request Declaration
	UPostMessagesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|ChatV2", DisplayName="Beam - Make PostMessages",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UPostMessagesRequest* Make(int64 _ObjectId, FString _RoomId, FString _Content, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMessagesSuccess, FBeamRequestContext, Context, UPostMessagesRequest*, Request, USendMessageResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMessagesError, FBeamRequestContext, Context, UPostMessagesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostMessagesComplete, FBeamRequestContext, Context, UPostMessagesRequest*, Request);

using FPostMessagesFullResponse = FBeamFullResponse<UPostMessagesRequest*, USendMessageResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostMessagesFullResponse, FPostMessagesFullResponse);
