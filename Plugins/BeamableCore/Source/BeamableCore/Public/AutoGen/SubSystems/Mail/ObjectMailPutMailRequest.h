
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/UpdateMailRequestBody.h"
#include "AutoGen/MailSuccessResponse.h"

#include "ObjectMailPutMailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectMailPutMailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UUpdateMailRequestBody* Body;

	// Beam Base Request Declaration
	UObjectMailPutMailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Body,_Expires,_Subject,_State,_Category,_bAcceptAttachments,Outer"))
	static UObjectMailPutMailRequest* MakeObjectMailPutMailRequest(int64 _ObjectId, FOptionalString _Body, FOptionalString _Expires, FOptionalString _Subject, FOptionalString _State, int64 _MailId, FOptionalString _Category, FOptionalBool _bAcceptAttachments, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPutMailSuccess, FBeamRequestContext, Context, UObjectMailPutMailRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPutMailError, FBeamRequestContext, Context, UObjectMailPutMailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectMailPutMailComplete, FBeamRequestContext, Context, UObjectMailPutMailRequest*, Request);

using FObjectMailPutMailFullResponse = FBeamFullResponse<UObjectMailPutMailRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectMailPutMailFullResponse, FObjectMailPutMailFullResponse);
