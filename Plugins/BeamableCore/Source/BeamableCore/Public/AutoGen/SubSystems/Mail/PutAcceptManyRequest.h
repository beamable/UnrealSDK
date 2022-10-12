
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/AcceptMultipleAttachments.h"
#include "AutoGen/MailSuccessResponse.h"

#include "PutAcceptManyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAcceptManyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UAcceptMultipleAttachments* Body;

	// Beam Base Request Declaration
	UPutAcceptManyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutAcceptManyRequest* MakePutAcceptManyRequest(int64 _ObjectId, TArray<int64> _MailIds, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAcceptManySuccess, FBeamRequestContext, Context, UPutAcceptManyRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAcceptManyError, FBeamRequestContext, Context, UPutAcceptManyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAcceptManyComplete, FBeamRequestContext, Context, UPutAcceptManyRequest*, Request);

using FPutAcceptManyFullResponse = FBeamFullResponse<UPutAcceptManyRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutAcceptManyFullResponse, FPutAcceptManyFullResponse);
