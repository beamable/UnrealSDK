
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/BulkSendMailRequestBody.h"
#include "AutoGen/MailSuccessResponse.h"

#include "ObjectMailPostBulkRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectMailPostBulkRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UBulkSendMailRequestBody* Body;

	// Beam Base Request Declaration
	UObjectMailPostBulkRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UObjectMailPostBulkRequest* MakeObjectMailPostBulkRequest(int64 _ObjectId, TArray<USendMailRequestBody*> _SendMailRequests, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPostBulkSuccess, FBeamRequestContext, Context, UObjectMailPostBulkRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPostBulkError, FBeamRequestContext, Context, UObjectMailPostBulkRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectMailPostBulkComplete, FBeamRequestContext, Context, UObjectMailPostBulkRequest*, Request);

using FObjectMailPostBulkFullResponse = FBeamFullResponse<UObjectMailPostBulkRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectMailPostBulkFullResponse, FObjectMailPostBulkFullResponse);
