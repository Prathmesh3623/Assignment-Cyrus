#include "BoxDataLoader.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"



bool FBoxDataLoader::ParseFromString(const FString& JsonString, FBoxDataRoot& OutData)
{
    TSharedPtr<FJsonObject> RootObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    if (!FJsonSerializer::Deserialize(Reader, RootObject) || !RootObject.IsValid())
        return false;

    OutData.Types.Empty();
    OutData.Objects.Empty();

    // Parse Types
    const TArray<TSharedPtr<FJsonValue>>* TypesArray;
    if (RootObject->TryGetArrayField(TEXT("types"), TypesArray))
    {
        for (auto& TypeVal : *TypesArray)
        {
            TSharedPtr<FJsonObject> Obj = TypeVal->AsObject();
            FBoxType NewType;
            NewType.Name = Obj->GetStringField(TEXT("name"));
            const TArray<TSharedPtr<FJsonValue>>& ColorArr = Obj->GetArrayField(TEXT("color"));
            NewType.Color = FLinearColor(
                ColorArr[0]->AsNumber() / 255.f,
                ColorArr[1]->AsNumber() / 255.f,
                ColorArr[2]->AsNumber() / 255.f
            );
            NewType.Health = Obj->GetIntegerField(TEXT("health"));
            NewType.Score = Obj->GetIntegerField(TEXT("score"));

            OutData.Types.Add(NewType);
        }
    }

    // Parse Objects
    const TArray<TSharedPtr<FJsonValue>>* ObjectsArray;
    if (RootObject->TryGetArrayField(TEXT("objects"), ObjectsArray))
    {
        for (auto& ObjVal : *ObjectsArray)
        {
            TSharedPtr<FJsonObject> Obj = ObjVal->AsObject();
            FBoxObject NewObj;
            NewObj.Type = Obj->GetStringField(TEXT("type"));

            TSharedPtr<FJsonObject> TForm = Obj->GetObjectField(TEXT("transform"));

            auto V = [](const TArray<TSharedPtr<FJsonValue>>& Arr) {
                return FVector(Arr[0]->AsNumber(), Arr[1]->AsNumber(), Arr[2]->AsNumber());
                };

            NewObj.Transform.Location = V(TForm->GetArrayField(TEXT("location")));
            NewObj.Transform.Rotation = FRotator::MakeFromEuler(V(TForm->GetArrayField(TEXT("rotation"))));
            NewObj.Transform.Scale = V(TForm->GetArrayField(TEXT("scale")));

            OutData.Objects.Add(NewObj);
        }
    }

    return true;
}
